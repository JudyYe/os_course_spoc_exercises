//
//  main.c
//  vtop
//
//  Created by Yakumorin on 16/3/9.
//  Copyright © 2016年 Yakumorin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
int mem[1<<12];
const int pdbr = 544;

/*
 --> pde index:0x1d  pde contents:80(valid 1, pfn 0x00)
 */
int pde(int pdbr, int va) {
    int base = 0;
    int pde_index = (va >> 10) & ((1<<5)-1);
    int pde_content = mem[pde_index + pdbr];
    
    int valid = (pde_content >> 7) & 1;
    if (valid == 0) {
        printf("pde fault");
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
        printf("pte fault");
        exit(0);
    } else {
        base = pte_content & ((1<<7) - 1);
        printf("\t\t--> pte index: 0x%2x pte contents: %2x(valid %d, pfn 0x%4x)\n", pte_index, pte_content, valid, base);
        base = base << 5;
    }
    return base;
}
/*     --> Translates to Physical Address 0xca8 --> Value: 16*/
int phy(int base, int va) {
    int offset = va & ((1<<5)-1);
    int value = mem[offset + base];
    printf("\t\t\t-->Translates to Physical Addres 0x%4x --> Value: %4x", offset + base, value);
    return value;
}

int main(int argc, const char * argv[]) {
 
    freopen("/Users/yakumorin/Documents/vtop/vtop/File", "r", stdin);
    int virtual_address;
    for(int i=0; i<(1<<7); ++i) {
        char s[20];
        scanf("%s", s);
        scanf("%s", s);
        for(int j=0; j<(1<<5); ++j)
            scanf("%x", &mem[(i<<5) + j]);
    }
    scanf("%x", &virtual_address);
    printf("%x\n", virtual_address);
    int ret = pde(pdbr, virtual_address);
    ret = pte(ret, virtual_address);
    ret = phy(ret, virtual_address);
    return 0;
}
