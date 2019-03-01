inherit ROOM;

void create()
{
        set("short", "梳妝台");
        set("long", @LONG
藏經殿有一泓碧泉如鏡，向稱美容泉。相傳為南陳後主妃在此避
亂時，對碧水照容顏梳妝打扮的地方。殿前勝跡有靈日，昔時夜間常
見飛光，或如繁星點點，或若萬螢亂飛，煞是壯觀。
LONG );
        set("exits", ([ 
               "north"   : __DIR__"cangjingdian",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6960);
	set("coor/y", -5520);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}