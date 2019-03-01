// Room: /heizhao/hzneitang.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "黑沼內堂");
        set("long", @LONG
內堂中間安了一張長桌，上面放著七盞油燈，排成天罡北鬥之
形。左首有一張椅上，地下蹲著一個頭發花白的女子，身披麻衫，
凝目瞧著地下一根根長約四寸，闊約二分，計數用的算子，顯然正
自潛心思索，雖聽得有人進來，卻不抬頭。
LONG );
        set("no_clean_up", 0);

        set("exits", ([
                "south" : __DIR__"hzyuanzi",
                "north" : __DIR__"hzneishi",
        ]));
        set("objects", ([
                //__DIR__"npc/yinggu" : 1,
                CLASS_D("dali") + "/yinggu" : 1,
        ]));
        set("coor/x", -5100);
        set("coor/y", -1480);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}