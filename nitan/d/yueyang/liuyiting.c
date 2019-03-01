// Room: /d/yueyang/liuyijing.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "柳毅傳書亭");
        set("long", @LONG
柳毅傳書後，洞庭龍王為了報答柳毅毅救女之恩，要將三公主嫁給
柳毅，柳毅認為救人于危難之中乃人之本份，不可因此而為謀利，婉言
謝絕了。柳毅出宮後，傾慕柳毅的龍女扮成漁家姑娘，與柳毅結成夫妻，
婚後才道破實情，與柳毅返回洞庭水府，柳毅被封王為洞庭王。
    人們為了紀念柳毅傳書，改桔井為柳毅井，並在井旁建有柳毅傳書
亭(ting)。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("item_desc", ([
                "ting" : "
      牧羊坡上遇青娥，為托傳書意若何？
      坐望直窮尋桔樹，莫道遙隔洞庭波。
 　 　龍宮弟子緘方啟，塵世朗君禍已多。
  　　留得舊時跡井在，井泉香冽出川阿。\n"
        ]));
        set("exits", ([
                "west" : __DIR__"liuyijing",
        ]));
        set("coor/x", -1680);
        set("coor/y", 2310);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}