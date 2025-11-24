#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10math.h>

class StaticBillboard {
public:
    struct VertexComponent {
        D3DXVECTOR3 pos;
        D3DXVECTOR2 UV;
    };

    ID3D11VertexShader* VertexShaderVS = nullptr;
    ID3D11PixelShader* PixelShaderPS = nullptr;
    ID3D11InputLayout* inputLayout = nullptr;
    ID3D11Buffer* vertexBuffer = nullptr;
    ID3D11Buffer* indexBuffer = nullptr;

    ID3D11ShaderResourceView* texture = nullptr;
    ID3D11SamplerState* sampler = nullptr;

    ID3D11Buffer* viewCB = nullptr;
    ID3D11Buffer* projCB = nullptr;
    ID3D11Buffer* worldCB = nullptr;

    ID3D11Device* d3dDevice = nullptr;
    ID3D11DeviceContext* d3dContext = nullptr;

    StaticBillboard(WCHAR* imagePath, ID3D11Device* device, ID3D11DeviceContext* context, float escala) {
        d3dDevice = device;
        d3dContext = context;

        // Cargar textura
        D3DX11CreateShaderResourceViewFromFile(d3dDevice, imagePath, nullptr, nullptr, &texture, nullptr);

        // Crear sampler
        D3D11_SAMPLER_DESC sampDesc;
        ZeroMemory(&sampDesc, sizeof(sampDesc));
        sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        d3dDevice->CreateSamplerState(&sampDesc, &sampler);

        // Crear quad con UVs fijos
        VertexComponent vertices[4] = {
            { D3DXVECTOR3(0, 0, -1 * escala), D3DXVECTOR2(0, 1) },
            { D3DXVECTOR3(0, 2 * escala, -1 * escala), D3DXVECTOR2(0, 0) },
            { D3DXVECTOR3(0, 2 * escala,  1 * escala), D3DXVECTOR2(1, 0) },
            { D3DXVECTOR3(0, 0,  1 * escala), D3DXVECTOR2(1, 1) }
        };

        D3D11_BUFFER_DESC vbDesc;
        ZeroMemory(&vbDesc, sizeof(vbDesc));
        vbDesc.Usage = D3D11_USAGE_DEFAULT;
        vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        vbDesc.ByteWidth = sizeof(vertices);

        D3D11_SUBRESOURCE_DATA vbData;
        vbData.pSysMem = vertices;
        d3dDevice->CreateBuffer(&vbDesc, &vbData, &vertexBuffer);

        // Índices
        UINT indices[6] = { 0,1,2, 0,2,3 };
        D3D11_BUFFER_DESC ibDesc;
        ZeroMemory(&ibDesc, sizeof(ibDesc));
        ibDesc.Usage = D3D11_USAGE_DEFAULT;
        ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        ibDesc.ByteWidth = sizeof(indices);

        D3D11_SUBRESOURCE_DATA ibData;
        ibData.pSysMem = indices;
        d3dDevice->CreateBuffer(&ibDesc, &ibData, &indexBuffer);

        // Crear constant buffers para matrices
        D3D11_BUFFER_DESC cbDesc;
        ZeroMemory(&cbDesc, sizeof(cbDesc));
        cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        cbDesc.ByteWidth = sizeof(D3DXMATRIX);
        cbDesc.Usage = D3D11_USAGE_DEFAULT;

        d3dDevice->CreateBuffer(&cbDesc, nullptr, &worldCB);
        d3dDevice->CreateBuffer(&cbDesc, nullptr, &viewCB);
        d3dDevice->CreateBuffer(&cbDesc, nullptr, &projCB);
    }

    void Draw(D3DXMATRIX vista, D3DXMATRIX proyeccion, float posX, float posY, float posZ) {
        unsigned int stride = sizeof(VertexComponent);
        unsigned int offset = 0;

        d3dContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
        d3dContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
        d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        d3dContext->PSSetShaderResources(0, 1, &texture);
        d3dContext->PSSetSamplers(0, 1, &sampler);

        // Matriz de mundo (solo traslación)
        D3DXMATRIX translation;
        D3DXMatrixTranslation(&translation, posX, posY, posZ);
        D3DXMatrixTranspose(&translation, &translation);

        d3dContext->UpdateSubresource(worldCB, 0, 0, &translation, 0, 0);
        d3dContext->UpdateSubresource(viewCB, 0, 0, &vista, 0, 0);
        d3dContext->UpdateSubresource(projCB, 0, 0, &proyeccion, 0, 0);

        d3dContext->VSSetConstantBuffers(0, 1, &worldCB);
        d3dContext->VSSetConstantBuffers(1, 1, &viewCB);
        d3dContext->VSSetConstantBuffers(2, 1, &projCB);

        d3dContext->DrawIndexed(6, 0, 0);
    }
};