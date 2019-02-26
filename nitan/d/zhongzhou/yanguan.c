inherit ROOM;

void create()
{
        set("short", "鴉片館");
        set("long", @LONG
一下樓梯走進一個大廳，原來這裏是一個鴉片館。大廳放
着大約有幾十張躺椅，幾個煙鬼躺在躺椅上，旁邊還有小
姐幫他做鴉泡。三面靠牆都放着躺椅。
LONG);
       set("exits", ([
                "up" : __DIR__"chalou",
                "east" : __DIR__"danjian",

       ]));
        set("coor/x", -9050);
	set("coor/y", -1020);
	set("coor/z", -10);
	setup();
}