// Room: /d/yueyang/shanliang.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "小山樑");
        set("long", @LONG
你站在一座小山樑上，遠處波帆點點，銀粼閃爍，晚歸晨起的漁歌
聲聲縈耳。近處，碧玉青螺般的君山如青龍橫臥萬頃洞庭湖波中，雞鳴
炊煙四起，一派世外桃源風光。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "northdown" : __DIR__"xiaolu4",
                "southdown" : __DIR__"erfeimu",
        ]));
        set("coor/x", -1670);
        set("coor/y", 2310);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}