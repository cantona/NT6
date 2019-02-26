// Room: /d/wuyi/shuiliandong.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "水簾洞");
        set("long", @LONG
水簾洞景區在天心巖北兩裏處，又名唐曜洞天，是武夷山最大的洞
穴，高、寬各三十丈許，上凸下凹，似斜覆的飛檐，崖內軒爽敞亮，有
三祀祠，奉祀宋朝大儒劉子翬（朱熹老師）、朱熹、劉珙。洞前有兩道
流淌的清泉，從三十丈米高的崖頂飄灑而下，宛若珠簾，散落在崖下浴
龍池中，人稱“赤壁千尋睛疑雨，明珠萬顆畫垂簾。”，“水簾知丈垂
丹壑，睛雪長年舞翠檐。”《武夷山志》稱其為“山中最勝之境”。徐
霞客稱其：“危崖千仞，上突下嵌，泉從巖頂墮下，巖既雄曠，泉亦高
散，千條萬縷，懸空傾瀉，亦大觀也”洞內巖壁上有許多摩崖石刻，篆
書“活源”二字，尤為引人注目。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "south" : __DIR__"path15",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1400);
        set("coor/y", -4880);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
