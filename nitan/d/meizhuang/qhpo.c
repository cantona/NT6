// qhpo.c
inherit ROOM;

void create()
{
        set("short", "奇槐坡");
        set("long", @LONG
這裏就是奇槐坡了，這裏種着大大小小，千奇百怪的槐樹，有的
槐樹一直向天，有的又曲折盤繞，你從這裏隱隱約約聽到一陣陣的琴
聲，似有似無，若隱若現。
LONG );
        set("outdoors", "meizhuang");
        set("exits", ([
            "eastup" : __DIR__"xiaodao",
            "west"  : __DIR__"senlin2",
        ]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}