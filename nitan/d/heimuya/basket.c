// Room: /d/heimuya/basket.c

inherit ROOM;
void create()
{
        set("short", "竹簍");
        set("long", @LONG
這是一隻大竹簍，足可裝得十來石米。抬頭上望，只見頭頂有天
風崖壁，這黑木崖着實高得厲害。
LONG );
        set("outdoors", "heimuya");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}