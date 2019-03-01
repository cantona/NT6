inherit ROOM;

void create()
{
        set("short", "驛站");
        set("long", @LONG
這裡是中州城的驛站，這個驛站不大，一邊是個小小的草
蓬，幾個官差在此落腳。
LONG);

        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"wendingnan4",
        ]));

        set("coor/x", -9030);
	set("coor/y", -1040);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}