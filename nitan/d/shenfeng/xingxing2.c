inherit ROOM;

void create()
{
        set("short", "星星峽");
        set("long", @LONG
峽內兩旁石壁峨然筆立，有如用刀削成，抬頭望天，只覺
天色又藍又亮，宛如潛在海底仰望一般。峽內巖石全是深黑色
顯得烏光發亮。道路彎來彎去，曲折異常。峽內初有積雪，黑
白相映，蔚為奇觀。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
                  "west" : __DIR__"caoyuan6",
                  "east" : __DIR__"xingxing1",
        ]));
        setup();
        replace_program(ROOM);
}