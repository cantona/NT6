// Room: /d/playertown/liaotianshi.c 聊天室
// Build 1999.12.10 bmw

inherit ROOM;
void create()
{
        set("short", "聊天室");
        set("long",
"這是一個很普通的房間，裏面只是樸素地擺着一些供人休息桌椅，一\n"
"名老翁熱情的招呼着客人。房間裏到處聚集着一羣羣的人，相互愉快着交\n"
"流着。在房間的右邊有一個小房間，偶爾有一些疲倦的人向右邊的房間離去。\n"
);
        set("no_fight", 1);

        set("exits", ([
                "north"  : __DIR__"miao",
        ]));
        setup();
        replace_program(ROOM);
}