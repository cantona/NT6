inherit ROOM;

void create()
{
        set("short", "石子小路");
        set("long", @LONG
這是一條用紫色和綠色小石子鋪成的小路，看着讓人格外的
不舒服。南面是一片祕密的小樹林，北面不遠是一排小籬笆。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"yz_door",
  "south" : __DIR__"xiaodao7",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
