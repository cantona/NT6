inherit ROOM;

void create()
{
        set("short","副殿");
        set("long",@LONG
這裏是凌霄城的副殿之一。幾個凌霄弟子正在一起，賊頭賊
腦地不知在幹什麼，鬼鬼祟祟的，準沒什麼好事。最近凌霄城裏
不太平，麻煩事情也挺多的，還是少理為妙。
LONG);
        set("exits",([
                    "east"  : __DIR__"lianwu2",
                    "west"  : __DIR__"dadian",
        ]));
        set("objects", ([
               __DIR__"npc/dizi" : 3,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
