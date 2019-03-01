inherit ROOM;

void create()
{
        set("short", "閉月亭");
        set("long", @LONG
亭上交纏薔薇、木香、刺梅、金雀，橋下撒滿鳳仙、雞冠、秋葵等種。
更有那金萱、百合、剪春羅、剪秋羅、滿地嬌、纏枝牡丹等類，不可枚舉。
遇開放之時，爛漫如錦屏。遠離數尺，盡植名花異草。一花未謝，一花又
開。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"jiyuan2",
        ]));

	set("coor/x", -6980);
	set("coor/y", 2140);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}