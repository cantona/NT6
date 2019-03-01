inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
轉過山樑，幾塊青石相互交搭，組成了一個避風的石崖。外
面朔風飛揚，裡面卻爐火熊熊，鬆木流爆，傳來絲絲烤肉的香味，
凌霄弟子巡山至此，常在這裡避風休憩。旁邊有個小店，疲累饑
渴時，可在裡面稍事休息。
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
            "westdown"  : __DIR__"sroad3",
            "east"  : __DIR__"bar", 
            "northup"  : __DIR__"sroad4",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
