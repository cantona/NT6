inherit ROOM;

void create()
{
        set("short", "藥莊小門");
        set("long", @LONG
這裏是一處籬笆小門，門邊有一塊小木牌上寫着“藥莊”兩
個篆字。南面是一條紫色和綠色小石子鋪成的小路。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"lu1",
  "north" : __DIR__"yz_xiaoyuan",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
