//
//  main.c
//  pageing
//
//  Created by YeJudy on 3/9/16.
//  Copyright © 2016 YeJudy. All rights reserved.
//

#include <stdio.h>

int mem[1<<12];

/*
 --> pde index:0x1d  pde contents:80(valid 1, pfn 0x00)
 */
int pde(int pdbr, int va) {
    int base = 0;
    int pde_index = (va >> 10) & ((1<<5)-1);
    int pde_content = mem[pde_index + pdbr];
    int valid = (pde_content >> 7) & 1;
    if (valid == 0) {
        printf("");
        exit(0);
    } else {
        base = pde_content & ((1<<7) - 1);
        printf("\t--> pde index: 0x%2x pde contents: %2x(valid %d, pfn 0x%4x\n", pde_index, pde_content, valid, base);
        base = base << 5;
    }
    return base;
}

/*pte index:0xb  pte contents:7f(valid 0, pfn 0x7f)*/
int pte(int base, int va) {
    int pte_index = (va >> 5) & ((1<<5)-1);
    int pte_content = mem[base + pte_index];
    int valid = (pte_content >> 7) & 1;
    if (valid == 0) {
        printf("");
        exit(0);
    } else {
        base = pte_content & ((1<<7) - 1);
        printf("\t\t--> pte index: 0x%2x pte contents: %2x(valid %d, pfn 0x%4x\n", pte_index, pte_content, valid, base);
        base = base << 5;
    }
    return base;
}
/*     --> Translates to Physical Address 0xca8 --> Value: 16*/
int phy(int base, int va) {
    int offset = va & ((1<<7)-1);
    int value = mem[offset + base];
    printf("\t\t\t-->Translates to Physical Addres 0x%4x --> Value: %4x", offset + base, value);
    return value;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int va;
    scanf("%4x", &va);
    pde(0, va);
    printf("Hello, World!\n");
    return 0;
}
