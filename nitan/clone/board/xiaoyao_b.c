// /clone/board/xiaoyao_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("逍遙派弟子留言板",({"board"}));
        set("location","/d/xiaoyao/qingcaop");
        set("board_id", "xiaoy_b");
        set("long", "這是供逍遙派門下留言的板子.\n");
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}
