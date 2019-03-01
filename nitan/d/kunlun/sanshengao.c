// Room: /d/kunlun/sanshengao.c 昆侖山三聖坳
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "三聖坳");
        set("long", @long
但見遍地綠草如錦，到處果樹香花。原來那三聖坳四周都是插天高
山，擋住了寒氣。昆侖派歷代掌門人曾花了極大力氣整頓這個山坳，派
遣弟子東至江南，西至天竺，搬移奇花異樹前來種植。忽聽得山坳後隱
隱傳出一陣琴聲，你好奇心起，便循聲尋去。
long );
        set("exits", ([
                "north" : __DIR__"jingshenfeng",
                "down"  :  __DIR__"fufengshan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "kunlun");
        set("coor/x", -119980);
        set("coor/y", 40170);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}