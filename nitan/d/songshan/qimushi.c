// Room: /d/songshan/qimushi.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "啟母石");
        set("long", @LONG
這裏有一壁三丈巨石當道。相傳大禹治水時要打通轅擐山，大禹化
熊扒挖不止。禹妻塗山氏送飯時不慎撞破，失驚而逃，到此化石。其時
塗山已有身孕，大禹追及喚子，巨石北裂一口，夏啟呱呱落地。巨石因
此喚作啟母石。
LONG );
        set("exits", ([
                "southeast" : __DIR__"shandao1",
                "west"      : __DIR__"qimuque",
                "northup"   : __DIR__"shandao2",
        ]));
        set("outdoors", "songshan");
        set("no_clean_up", 0);
        set("coor/x", -10);
        set("coor/y", 750);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}