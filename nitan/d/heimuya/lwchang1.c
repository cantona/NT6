// lwchang1.c
// By haiyan

inherit ROOM;

void create()
{
        set("short", "練武場");
        set("long", @LONG
這裏是日月神教的練武場，場上立着幾個木人，教中眾弟子常在
此處修煉邪功，四周充滿着詭祕色彩。
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
