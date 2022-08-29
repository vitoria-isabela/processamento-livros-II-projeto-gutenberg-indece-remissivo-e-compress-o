[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=8158511&assignment_repo_type=AssignmentRepo)
# Trabalho 2: índice Remissivo e Compressão

## Datas Importantes:

Ponto de controle na aula: 25/07(Turma A) 26/07 (Turma B)
Data de entrega do código: 14/08 (Ambas as turmas)
Entrevistas: agendadas 15/08 (Turma A) 16/08 (Turma B)
Objetivos

Na primeira parte do trabalho, o Projeto Gutenberg foi utilizado para processar arquivos texto ASCII e encontrar as palavras mais frequentes de cada livro e de um total de 10 livros processados. 

Para esta segunda parte, será implementado o índice remissivo das palavras mais frequentes encontradas. O índice remissivo é aquele que mostra para cada palavra, as páginas que elas aparecem no texto. Neste trabalho, ao invés de considerar as páginas onde essas palavras aparecem, iremos exibir as linhas. Além disso, para otimizar o armazenamento, deve-se implementar também um método de compressão.  

## Métodos

### Busca Digital 

Para implementar o índice remissivo, deve ser utilizada uma Árvore de Busca Digital (ABD). Tais estruturas consideram que cada nó contém um dígito (caractere) que compõe a chave. 

Implementar uma árvore de busca digital (o tipo fica a escolha de cada grupo) para armazenar cada palavra contendo ao final da chave uma lista com os números das linhas que a palavra aparece no texto.

Tipo Abstrato de Dados: ABD (árvore de busca digital escolhida)
- Construtor: Cria uma árvore de busca digital vazia
- Insert: insere uma nova palavra no TAD
- Search: Dada uma palavra deve retornar o nó da árvore (ponteiro para lista com as linhas).
- Destrutor:  desaloca a memória.


### Método de Compressão

A compactação de dados é a ciência (e arte) de representar informações de forma compacta. Tem sido, por décadas,  uma das tecnologias críticas para a revolução multimídia digital. Sem as técnicas de compressão,  Internet, TV digital, comunicação móvel ou a crescente comunicação por vídeo não teriam uma sustentação prática.

Por 'comprimir dados', na verdade queremos dizer derivar técnicas ou, mais especificamente, projetar algoritmos eficientes para:
representar dados de forma menos redundante
remover a redundância nos dados
implementar codificação, incluindo codificação e decodificação
As técnicas de compressão de dados são motivadas principalmente pela necessidade de melhorar a eficiência do processamento da informação. Isso inclui melhorar os seguintes aspectos principais no domínio digital:
eficiência de armazenamento
uso eficiente da largura de banda de transmissão
redução do tempo de transmissão

Na literatura há diferentes esquemas de compressão para diferentes tipos de dados, por exemplo: MP3 para áudio, MP4 ou avi para vídeo, jpeg para imagem e zip para dados gerais. 

**Código  de Huffman**

A codificação Huffman é um método de compactação bem-sucedido usado originalmente para compactação de texto. Ele assume que cada caractere é armazenado como um código ASCII de 8 bits. Cada caractere da string original é convertido em uma pequena cadeia de bits, que é o seu código. A ideia do algoritmo de Huffman consiste em  usar códigos curtos para os caracteres que ocorrem com frequência e deixar os códigos mais longos para os caracteres mais raros.  Os códigos são, portanto, de comprimento variável.  

Neste trabalho, vocês devem implementar a codificação de huffman. Vocês deverão criar a tabela de frequências, codificar o texto e escrever a codificação em um arquivo binário. 


## Experimentos

### Caso 1: Testes Unitários
Devem ser implementados testes unitários tanto para testar os retornos das funções da ABD escolhida quanto dos algoritmos de compressão utilizados.
Observação: Testes unitários não são a mesma coisa que arquivos executáveis que chamam as funções. Utilize rotinas específicas que conferem se o retorno das funções implementadas está de acordo com o que foi implementado. 

### Caso 2: Gerar Índice Remissivo de um livro.

Aqui, deve-se aplicar ABD para a geração dos índices remissivos. O programa deve ler um livro e gerar um arquivo de saída onde cada linha do arquivo deve conter a palavra e lista de linhas onde ocorrem no arquivo original. As palavras devem estar em ordem alfabética. Somente devem ser impressas as 50 palavras mais frequentes. 
			

### Caso 3: taxas de compressão: huffman
		
Para cada livro, vocês deverão aplicar o algoritmo de compressão e deverão calcular a taxa de compressão. A taxa de compressão é obtida pela relação entre o tamanho do arquivo comprimido e o tamanho do arquivo original. 

**BÔNUS**: Ganhará pontuação extra se implementar um segundo algoritmo de compressão e realizar um estudo comparativo entre os métodos.

## Entrega

Antes de iniciar, crie um rótulo para a parte 1 do trabalho que já foi entregue. Por exemplo: release "versão 1".
O grupo deve usar seu arquivo REPORT.md para explicar a abordagem empregada para solucionar a tarefa: como foi a distribuição das tarefas entre os membros, escolhas de algoritmos, o que funcionou ou o que não funcionou, mudanças de planos, etc. Tente resumir todas as diferentes maneiras pelas quais você desenvolveu, avaliou e melhorou seu código.
Mantenha o repositório do grupo sempre atualizado. O histórico de atualizações e as contribuições individuais será usado para verificar a distribuição de tarefas entre os membros do grupo.
Após o encerramento do prazo de entrega, o código que será avaliado será aquele que estiver no branch principal do grupo.
O grupo deve se preparar para apresentar o trabalho que foi desenvolvido seguido de entrevista a ser agendada com o/a professor/a.

## Critérios da Avaliação

- (F) Funcionalidade (50%): Será observado se todas as funcionalidades estão gerando os resultados esperados de acordo com a especificação dada acima; se a especificação for ambígua e você tiver que fazer uma determinada escolha, defenda essa escolha em seu arquivo REPORT.
- (D) Desempenho (15%): refere-se a quão rápido e/ou utilização eficiente de memória seu programa pode produzir os resultados requeridos em comparação com outras submissões.
- (T) Testes (10%) : refere-se à adequação dos testes de unidade para todas as classes de estrutura de dados desenvolvidos nesta tarefa.
- (E) Estilo (15%) : refere-se ao estilo de programação C/C++, incluindo coisas como indentação consistente, nomes de identificadores apropriados, comentários úteis, etc.
- (O) Organização (10%): refere-se a estruturação do projeto, diretórios, projeto cmake, etc

Nota final calculada será dada então por:
NF = (F + D + T + E + O)* I.
Onde I é o fator de contribuição individual considerando relatório e a entrevista.

