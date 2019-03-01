// lwchang1.c
// By haiyan

inherit ROOM;

void create()
{
        set("short", "練武場");
        set("long", @LONG
這裡是日月神教的練武場，場上立著幾個木人，教中眾弟子常在
此處修煉邪功，四周充滿著詭秘色彩。
LONG );
        set("exits", ([
            "west"      : __DIR__"midao02",
        ]));
        set("objects", ([
            "/clone/npc/mu-ren" : 4,
        ]));

        setup();
        replace_program(ROOM);
}
