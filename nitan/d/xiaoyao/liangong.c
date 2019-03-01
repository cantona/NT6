// liangong.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "石屋");
        set("long", @LONG
這是樹林中的一間石屋，屋內顯得什麼清凈和簡樸，房間中除了一
副棋盤外，並沒有什麼特別的擺設在這裡，不會受到任何東西的騷擾，
是個修煉內功的好地方。
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "south" : __DIR__"xiaodao4",
        ]));
        set("objects", ([ /* sizeof() == 2 */
                CLASS_D("xiaoyao")+"/fanbailing" : 1,
        ]));
        set("coor/x", 90);
        set("coor/y", -490);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}