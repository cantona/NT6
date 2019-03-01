//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "歸元寺");
        set ("long", @LONG
一座清幽禪院。據說寺中藏有印度、斯裡蘭卡、緬甸、泰國、日本
等國相贈的佛經，還有橡木韋馱雕像、白玉佛像、五百羅漢像和千手觀
音像等寶物。
LONG);
        set("exits", ([
                "west" : __DIR__"hzjie5",
        ]));
  
        set("no_clean_up", 0);
	set("coor/x", -5080);
	set("coor/y", -1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}