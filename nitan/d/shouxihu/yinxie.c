// Room: /yangzhou/yinxie.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","春草池塘");
        set("long",@LONG
春草池塘吟榭面東三楹。榭內懸姚元三題匾，外柱懸掛魏之禎所書
集杜牧、韋莊詩句楹聯(lian)。
LONG );
        set("outdoors", "shouxihu");
        set("item_desc", ([
                "lian" : "
        碧        綠
        落        波
        青        春
        山        浪
        飄        滿
        古        前
        韻        陂
\n",
        ]));
        set("exits", ([
                "east" : __DIR__"taohuawu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -1);
        set("coor/y", 40);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}