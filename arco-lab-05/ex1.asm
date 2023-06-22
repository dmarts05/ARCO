    .data
resultado: .word 0

    .text
    .globl main
main:
    # El objetivo del programa es implementar la siguiente función:
    # f(a,b,c,d) = 3a + 2(c - 2d) - 5b

    # La función debe ejecutarse 10 veces usando un bucle

    # Comenzamos por cargar los valores de a, b, c y d en los registros
    li t0, 7 # a = 7
    li t1, 2 # b = 2
    li t2, 4 # c = 4
    li t3, 3 # d = 3

    # Cargamos el contador del bucle (son 10 iteraciones pero la primera no cuenta)
    li t6, 11
bucle:
    # Realizamos el cálculo de la expresión
    slli t4, t0, 1 # t4 = 2a
    add t4, t4, t0 # t4 = 3a
    slli t5, t3, 1 # t5 = 2d
    sub t5, t2, t5 # t5 = c - 2d
    slli t5, t5, 1 # t5 = 2(c - 2d)
    add t4, t5, t4 # t4 = 3a + 2(c - 2d)
    slli t5, t1, 2 # t5 = 4b
    add t5, t5, t1 # t5 = 5b
    sub t4, t4, t5 # t4 = 3a + 2(c - 2d) - 5b
    
    # Obtenemos puntero a memoria
    la t5, resultado

    # Guardamos el resultado en memoria
    sw t4, 0(t5)

    # Actualizamos los valores de a, b, c y d
    addi t0, t0, 1 # a = a + 1
    slli t1, t1, 1 # b = b * 2
    slli t2, t2, 2 # c = c * 4
    slli t3, t3, 1 # d = 2d
    addi t3, t3, -1 # d = 2d - 1

    # Decrementamos el contador del bucle
    addi t6, t6, -1

    # Comprobamos si hemos llegado al final del bucle
    bne t6, zero, bucle

    # Estamos fuera del bucle

    # Imprimimos el resultado
    lw a0, resultado
    li a7, 1
    ecall

    # Terminamos el programa
    li a7, 10
    ecall