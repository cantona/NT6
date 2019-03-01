//ROOM: /d/yanziwu/qiushuan.c

inherit ROOM;

void create()
{
        set("short", "秋爽齋");
        set("long", @LONG
素幔低垂，設備樸素，臨窗的桌上堆滿卷軸，一大桶毛筆顯示出
主人學識淵博。一只劍形花瓶插著幾朵犁花，帶來幾分清新的氣息。
LONG );
        set("exits", ([
            "east" : __DIR__"canheju",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}