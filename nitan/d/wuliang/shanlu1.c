// Room: /wuliang/shanlu1.c
// Date: Oct.18 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這是一條通向深山的小路。兩邊都是茂密的長草和樹林。偶爾有
小鳥飛過。林間時而傳出一陣野獸的嘶嚎或呦呦的鹿鳴。
LONG );
        set("outdoors", "wuliang");
        set("no_clean_up", 0);
        set("exits", ([
                "eastdown" : "/d/dali/shanlu4",
                "westup"   : __DIR__"shanlu2",
        ]));
        set("coor/x", -70000);
        set("coor/y", -80000);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}