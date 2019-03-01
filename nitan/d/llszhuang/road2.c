inherit ROOM;
void create()
{
        set("short", "平原路");
        set("long",
"大道自西向東，地勢漸平。路面舖著小石子，光腳走上去，覺得頗為\n"
"硌腳。道兩旁的樹木越來越少，驕陽似火，令人真想找個地方休息一下，\n"
"正好前面有家小酒館。\n"
);
        set("exits", ([
  "east" : __DIR__"road1",
  "northwest" : __DIR__"inn",
]));
        set("outdoors", "llszhuang");
        setup();
}
