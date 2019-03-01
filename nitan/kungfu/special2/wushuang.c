// wushuang.c 國士無雙
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "國士無雙" NOR; }

int perform(object me, string skill)
{
        return notify_fail("此天性者城府極深，善于隱藏自己的特性，\n"
                           "讓人揣摩不透。此天性者無論修煉何種武\n"
                           "功，均不考慮武功中關于天性的限制。\n");
}