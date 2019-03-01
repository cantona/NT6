inherit ROOM;

void create()
{
        set("short", "廚房");
        set("long", @LONG
這裡是一間廚房。廚房很大，可能也是因為兼作倉庫的緣故。灶
頭砌在北首，一根大煙囪直通出屋頂。房子四壁被常年煙火熏得發黑，
連房樑也是焦黑焦黑。牆角堆滿了柴火，另一邊放了些曬幹的辣椒，
稻谷等。東邊的牆灰剝落了一塊，露出犬牙交錯的磚縫來。屋角邊有
個大洞。
LONG );
        set("exits", ([
                "southwest" : __DIR__"houshan",
        ]));
        setup();
        replace_program(ROOM);
}