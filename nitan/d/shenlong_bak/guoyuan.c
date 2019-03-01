// /d/shenlong/guoyuan.c
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "果園");
        set("long", @LONG
這是一片果園，種的是一些水果，有蘋果、梨頭、山楂、桃子、杏
子、梅子等，有的已到的收獲時節，枝頭已被果實壓彎了腰，沉甸甸的，
風一吹枝頭一顫一顫的，叫人看了直流口水。西面、北面似乎仍是農田，
南面是山丘，東面是一道山崗。
LONG
        );
        set("outdoors", "shenlong");
        set("exits", ([
                "south" : __DIR__"shanqiu",
        ]));
        set("objects", ([
                FRUIT_DIR"apple" : random(2),
                FRUIT_DIR"lizi" : random(2),
                FRUIT_DIR"taozi" : random(2),
                FRUIT_DIR"xingzi" : random(2),
                FRUIT_DIR"yangmei" : random(2),
        ]));
        set("snaketype", ({"jinhuan"}));
        setup();
}

#include "snakeroom.h";
