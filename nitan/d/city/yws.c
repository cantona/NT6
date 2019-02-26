// Room: /d/city/yws.c
// This is a room made by roommaker. write by Fan. :)

inherit ROOM;

void create()
{
	set("short", "醫務室");
        set("long", @LONG
這裏是擂台旁邊的醫務室，專門用來搶救因比武后重傷的江湖人
士。醫務室的左邊放着一個大藥櫃，裏面有各式各樣的藥品，在右邊
是一張休息用的牀，是用來給受傷的休息之用。
LONG );
	set("sleep_room", "1");
	set("exits", ([ /* sizeof() == 1 */
  "out" : "/d/city/leitai.c",
]));
	set("no_clean_up", 0);

	setup();
}
void init()
{
        add_action("do_get","get");
        add_action("do_drop","drop");
}
int do_get()
{
        write(query("name", this_player())+"！！那麼多手多腳做什麼！！\n");
        return 1;
}
int do_drop()
{
        write(query("name", this_player())+"！！別亂丟東西！！\n");
        return 1;
}
