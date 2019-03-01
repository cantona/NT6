// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "七夕台");
        set("long", @LONG
圓緣台東，又是一座平台，鐫有一碑，題名『七夕』。七夕台修
葺得相當整齊潔凈，面懸崖的一邊攔了一排漢白玉石闌幹。憑闌遠眺，
霧靄溟蒙，白雲盪漾。每到星夜，在七夕台觀到的牛郎織女星總是分
外明亮。千種纏綿、萬般恩愛濃得似乎能夠傳到人間。難怪詞人雲：
纖雲弄巧，飛星傳恨，銀漢迢迢暗度。金風玉露一相逢，便勝卻、人
間無數；柔情似水，佳期如夢，忍顧鵲橋歸路。兩情若是久長時，又
豈在、朝朝暮暮。　
LONG );
        set("outdoors", "xihu");
        set("exits", ([
                "north" : "/d/hangzhou/sansheng-shi",
                "west" : "/d/hangzhou/yuanyuan-tai",
        ]));

//        set("no_clean_up", 0);
	set("coor/x", 780);
	set("coor/y", -1970);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}