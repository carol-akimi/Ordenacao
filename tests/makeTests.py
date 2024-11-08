import random

def gerar_valores_aleatorios(quantidade, caminho_arquivo):
    # Gerar a lista de valores aleatórios
    valores = [str(random.randint(1, quantidade)) for _ in range(quantidade)]
    
    # Escrever os valores no arquivo, separados por espaços
    with open(caminho_arquivo, 'w') as arquivo:
        arquivo.write(" ".join(valores))

# Parâmetros
quantidade_valores = 100000  # Defina a quantidade desejada
caminho_arquivo = "tests/random/100000_5.in"

# Gerar e salvar os valores
gerar_valores_aleatorios(quantidade_valores, caminho_arquivo)
