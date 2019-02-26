// Room: /d/ruzhou/jiao1.c  結婚的花轎
// llm 99/06

inherit ROOM;

void create()
{
        set("short", "花轎");
        set("long", @LONG
你正坐在一頂大花轎裏，裏面空間不大，上襯綾綢、下墊軟毯，人在
裏面只覺一顛一顛地搖晃着，分明是在行走之中。
LONG
        );

        set("exits", ([
        ]));

        setup();
        replace_program(ROOM);
}


