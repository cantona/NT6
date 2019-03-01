inherit ROOM;

void create()
{
        set("short", "小橋");
        set("long", @LONG 
這是一座江南園林似的小橋，橋下蓮葉田田，清波盪漾，水
滑欄碧，池魚自得。城外雖有雪花飛舞之姿，朔風呼號之勢，此
處卻得地氣溫暖之潤，得天獨厚，有如江南之景，現于西域大漠
之地。
LONG);
        set("outdoors", "lingxiao");
        set("exits",([
                    "south"  : __DIR__"houyuan2",  
                    "north"  : __DIR__"book", 
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);

}
