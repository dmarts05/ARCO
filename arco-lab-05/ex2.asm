    .data
resultado: .word 0

    .text
    .globl main
main:
    # Inicializamos los primeros dos términos de la sucesión
    li t0, 0 # Primer término = 0
    li t1, 1 # Segundo término = 1

    # Inicializamos el contador del bucle y el límite de términos a calcular
    li t2, 2 # Empezamos en el tercer término
    li t3, 25 # Calculamos 25 términos en total
bucle:
    # Calculamos el siguiente término de la sucesión
    add t4, t0, t1 # t4 = primer término + segundo término

    # Obtenemos puntero a memoria
    la t5, resultado

    # Almacenamos el valor en memoria
    sw t4, 0(t5)

    # Movemos los términos para calcular el siguiente
    mv t0, t1 # El segundo término se convierte en el primer término
    mv t1, t4 # El valor calculado se convierte en el segundo término

    # Verificamos si hemos alcanzado el límite de términos
    bge t2, t3, fin

    # Incrementamos el contador del bucle y volvemos al inicio del bucle
    addi t2, t2, 1
    j bucle
fin:
    # Imprimimos el resultado
    lw a0, resultado
    li a7, 1
    ecall

    # Terminamos el programa
    li a7, 10
    ecall