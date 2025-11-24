#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11.h>
#include <d3dx10tex.h>
#include <wrl/client.h>
#include <string>

using namespace std;

struct Vertex {
	D3DXVECTOR3 position;
	D3DXVECTOR2 uv;
};

struct CB_Transform {
	D3DXMATRIX world;
};

Vertex vertices[4] = {
	{ D3DXVECTOR3(-0.5f,  0.5f, 0.0f), D3DXVECTOR2(0.0f, 0.0f) }, // Arriba izquierda
	{ D3DXVECTOR3(0.5f,  0.5f, 0.0f), D3DXVECTOR2(1.0f, 0.0f) }, // Arriba derecha
	{ D3DXVECTOR3(-0.5f, -0.5f, 0.0f), D3DXVECTOR2(0.0f, 1.0f) }, // Abajo izquierda
	{ D3DXVECTOR3(0.5f, -0.5f, 0.0f), D3DXVECTOR2(1.0f, 1.0f) }  // Abajo derecha
};


class Sprite2D {
private:
	ID3D11Texture2D* texture = nullptr;				// La textura en si
	ID3D11Device* device = nullptr;					// Device para crear recursos
	ID3D11VertexShader* vertexShader = nullptr;		// Shader para procesar los vertices
	ID3D11PixelShader* pixelShader = nullptr;		// Shader para dibujar la textura
	ID3D11ShaderResourceView* srv = nullptr;		// Con esto puedo mandar la textura al pixel shader
	ID3D11Buffer* vertexBuffer = nullptr;			// Esto para dibujar los triangulos
	ID3D11InputLayout* inputLayout = nullptr;		// Define la estructura del vertice
	ID3D11Buffer* constantBuffer = nullptr;		// Para enviar matrices al vertex shader

	string name;
	string pathTexture;
	float posX;
	float posY;
	float scaleX;
	float scaleY;


public:
	Sprite2D(string name_, string path_) : name(name_), pathTexture(path_), posX(0), posY(0), scaleX(1), scaleY(1) {}

	void setPosition(float pX_, float pY_) {
		posX = pX_;
		posY = pY_;
	}

	void setScale(float sX_, float sY_) {
		scaleX = sX_;
		scaleY = sY_;
	}

	// Carga la textura desde archivo y crea el vertex buffer
	void setDevice(ID3D11Device* device_) {
		device = device_;

		wstring wPathTexture(pathTexture.begin(), pathTexture.end());
		ID3D11Resource* resource = nullptr;
		HRESULT hr = D3DX11CreateTextureFromFile(device_, wPathTexture.c_str(), nullptr, nullptr, &resource, nullptr);
		if (SUCCEEDED(hr) && resource) {
			resource->QueryInterface(__uuidof(ID3D11Texture2D), (void**)&texture);
			resource->Release();
		}

		if (texture) {
			device->CreateShaderResourceView(texture, nullptr, &srv);
		}

		// Crear vertex buffer para el quad porque lo necesitaremos para dibujar
		D3D11_BUFFER_DESC bd = {};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(vertices);
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = vertices;

		device->CreateBuffer(&bd, &initData, &vertexBuffer);

		D3D11_BUFFER_DESC cbd = {};
		cbd.Usage = D3D11_USAGE_DEFAULT;
		cbd.ByteWidth = sizeof(CB_Transform);
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		device->CreateBuffer(&cbd, nullptr, &constantBuffer);
	}

	// Asigna el vertex shader para procesar los vertices
	void setVertexShader(ID3D11VertexShader* vShader_, ID3DBlob* vsBytecode) {
		vertexShader = vShader_;

		D3D11_INPUT_ELEMENT_DESC layout[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, offsetof(Vertex, uv),       D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		device->CreateInputLayout(
			layout,
			ARRAYSIZE(layout),
			vsBytecode->GetBufferPointer(),
			vsBytecode->GetBufferSize(),
			&inputLayout
		);
	}


	// Asigna el pixel shader para dibujar la textura
	void setPixelShader(ID3D11PixelShader* pShader_) {
		pixelShader = pShader_;
	}

	void draw(ID3D11DeviceContext* context) {
		if (!context || !vertexBuffer || !vertexShader || !pixelShader || !srv)
			return;

		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		context->VSSetShader(vertexShader, nullptr, 0);
		context->PSSetShader(pixelShader, nullptr, 0);
		context->PSSetShaderResources(0, 1, &srv);
		context->IASetInputLayout(inputLayout);

		D3DXMATRIX scale, translate, finalMatrix;
		D3DXMatrixScaling(&scale, scaleX, scaleY, 1.0f);
		D3DXMatrixTranslation(&translate, posX, posY, 0.0f);
		finalMatrix = scale * translate;

		CB_Transform cb;
		cb.world = finalMatrix;

		context->UpdateSubresource(constantBuffer, 0, nullptr, &cb, 0, 0);
		context->VSSetConstantBuffers(0, 1, &constantBuffer);

		context->Draw(4, 0);
	}

};
