//ROOM: /d/yanziwu/qinfang2.c

inherit ROOM;
void create()
{
        set("short", "沁芳閣二層");
        set("long", @LONG
這兒窗户半閉，嗅着透過來的陣陣清香，你覺得有些睏倦。一張
大牀上淡綠色的被褥發出淡淡的香氣，睡了吧，你不由的想到。
LONG );
        set("exits", ([
            "down"    : __DIR__"qinfang1",
        ]));
        set("sleep_room", 1);
        set("no_fight", 1);
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}