### Instruções para manipulação do objeto:
- Movimentação da câmera para esquerda / direita: tecla A / tecla D;
- Zoom In: tecla W;
- Zoom Out: tecla S

### Arquivo de configuração
[Arquivo](./CG20221/Intro3D/Models/scene_config.txt)
- Câmera: os atributos "pos", "front" e "up" são definidos nas primeiras linhas do arquivo, respectivamente;
- Objetos: são declarados logo após, informando o nome do arquivo OBJ

Exemplo:

```
camPos 0 0  3
camFrn 0 0 -1
camUpv 0 1  0
objPikachu.obj
```