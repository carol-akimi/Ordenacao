def gerar_valores_ordenados(quantidade, caminho_arquivo, ordem):
    # Gerar a lista de valores ordenados
    if ordem == "crescente":
        valores = list(range(1, quantidade + 1))
    elif ordem == "decrescente":
        valores = list(range(quantidade, 0, -1))
    else:
        raise ValueError("Ordem deve ser 'crescente' ou 'decrescente'")
    
    # Escrever os valores no arquivo, separados por espaços
    with open(caminho_arquivo, 'w') as arquivo:
        arquivo.write(" ".join(map(str, valores)))

# Parâmetros
quantidade_valores = 100  # Quantidade desejada de valores
caminho_arquivo = "tests/reversed/100.in"
ordem = "decrescente"  # Pode ser 'crescente' ou 'decrescente'

# Gerar e salvar os valores ordenados
gerar_valores_ordenados(quantidade_valores, caminho_arquivo, ordem)
