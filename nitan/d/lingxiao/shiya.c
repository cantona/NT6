inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
轉過山樑，幾塊青石相互交搭，組成了一個避風的石崖。外
面朔風飛揚，裏面卻爐火熊熊，松木流爆，傳來絲絲烤肉的香味，
凌霄弟子巡山至此，常在這裏避風休憩。旁邊有個小店，疲累飢
渴時，可在裏面稍事休息。
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
