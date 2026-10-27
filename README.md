# Árvore Rubro-Negra (Red-Black Tree)

Implementação computacional em **C++** de uma **Árvore Binária de Busca Auto-Balanceada (Red-Black Tree)**, desenvolvida para a disciplina de Estrutura de Dados.

O objetivo desta estrutura é manter o equilíbrio da árvore durante as operações de inserção e remoção utilizando propriedades de coloração de nós (`VERMELHO` / `PRETO`) e rotações, garantindo um tempo de execução de **$O(\log n)$** para busca, inserção e remoção.

## Funcionalidades

O programa conta com um menu interativo via terminal com as seguintes operações:

- **1. Inserir:** Adiciona novos elementos na árvore (inicialmente como nós vermelhos) e executa o ajuste (`Ajustar`) com rotações/recolorações para preservar o balanceamento.
- **2. Remover:** Localiza e remove o nó desejado, utilizando `transplantar` para substituir pelo sucessor e `Corrigir` para reequilibrar a altura negra da árvore.
- **3. Buscar:** Realiza a busca recursiva de um valor na árvore.
- **4. Exibir:** Imprime a estrutura da árvore em **Pré-Ordem** (*raiz $\rightarrow$ esquerda $\rightarrow$ direita*), indicando a cor de cada nó (`V` para Vermelho, `P` para Preto).

## Propriedades Garantidas

1. **Coloração:** Todo nó é **Vermelho** ou **Preto**.
2. **Raiz:** A raiz é sempre **Preta**.
3. **Nós Vermelhos:** Não existem dois nós vermelhos consecutivos (filhos de um nó vermelho são sempre pretos).
4. **Altura Negra:** Todo caminho da raiz até qualquer folha nula contém a mesma quantidade de nós pretos.

## Tecnologias Utilizadas

- **C++11** (ou superior)
- Manipulação direta de ponteiros e alocação dinâmica de memória (`struct`, `new`, `delete`)
1. Clone o repositório ou baixe os arquivos:
   ```bash
   git clone [https://github.com/JoanaFelizardo/Arvore_Rubro_Negra.git](https://github.com/JoanaFelizardo/Arvore_Rubro_Negra.git)
