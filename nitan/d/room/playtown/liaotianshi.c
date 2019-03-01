// Room: /d/playertown/liaotianshi.c 聊天室
// Build 1999.12.10 bmw

inherit ROOM;
void create()
{
        set("short", "聊天室");
        set("long",
"這是一個很普通的房間，裡面只是樸素地擺著一些供人休息桌椅，一\n"
"名老翁熱情的招呼著客人。房間裡到處聚集著一群群的人，相互愉快著交\n"
"流著。在房間的右邊有一個小房間，偶爾有一些疲倦的人向右邊的房間離去。\n"
);
        set("no_fight", 1);

        set("exits", ([
                "north"  : __DIR__"miao",
        ]));
        setup();
        replace_program(ROOM);
}