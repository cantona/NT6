// Room: /d/wizard/wizard_room.c

inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
        set("short", "巫師休息室");
        set("long", @LONG
這裏就是泥潭巫師的休息所在，剛粉刷過的四周牆壁上光禿禿的
什麼都沒有，屋子的正中央放着一張楠木桌，上面擺着一本巫師留言
簿(board)。地上則是零零碎碎的一些BUG，到處亂爬。
LONG );

        set("exits", ([
               "down" : __DIR__"guest_room",
               "up" : __DIR__"meeting_room",
               "west" : __DIR__"debug_room",
        ]));
        set("valid_startroom", 1);
        set("no_fight", "1");
        set("coor/x", 10000);
        set("coor/y", 10000);
        set("coor/z", 10000);
        setup();

        call_other("/clone/board/wiz_b", "???");
        replace_program(ROOM);
}
