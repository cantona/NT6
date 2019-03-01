inherit ROOM;
void create()
{
        set("short", "山中小路");
        set("long",
"這裡山色甚是凄涼，道路更本來已是苔蘚土滑，崎嶇難行到後來更是\n"
"亂山崢嶸，荒草沒徑。路邊灌木叢生，每叢灌木上都長滿了長達寸許的木\n"
"刺，木刺上還掛著各種顏色的布條。\n"
);
        set("exits", ([
  "west" : __DIR__"road2",
  "eastdown" : __DIR__"road",
]));
        set("outdoors", "llszhuang");
        setup();
}
