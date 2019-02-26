// linzhennan.c 林震南

#include <ansi.h>;

inherit NPC;

int ask_fuwei();
int ask_yuantu();
int ask_bixie();
int ask_tong();
int ask_baobiao();

string * destcity = ({
        "北京",
        "襄陽",
});
string * destmanager = ({
        "yi biaotou",
        "liu biaotou",
});
void create()
{
        set_name("林震南", ({ "lin zhennan", "lin", "zhennan" }));
        set("title", HIR"福"HIC"威"YEL"鏢局"HIY"總鏢頭"NOR);
        set("gender", "男性");
        set("age", 45);
        set("long", "他就是「福威鏢局」的總鏢頭－－林震南。\n");

        set("combat_exp", 30000);
        set("shen_type", 1);

        set("max_neili", 500);
        set("neili", 500);
        set("jiali", 10);

        set_skill("force", 40);
        set_skill("sword", 50);
        set_skill("bixie-sword", 50);
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
        map_skill("parry", "bixie-sword");
        map_skill("sword", "bixie-sword");

        set("inquiry", ([
                "向陽老宅" : "林震南説道：那是我從前在福建時住的家院，已經破敗了。\n",
                "福威鏢局" : (: ask_fuwei :),
                "遠圖公" : (: ask_yuantu :),
                "林遠圖" : "林震南大怒：小孩子這麼沒禮貌，直呼先人名諱！\n",
                "辟邪劍法" : (: ask_bixie:),
                "銅錢" : (: ask_tong:),
                "銅板" : (: ask_tong:),
                "task" : (: ask_baobiao :),
                "護鏢" : (: ask_baobiao :),
                "押鏢" : (: ask_baobiao :),
                "保鏢" : (: ask_baobiao :),
        ]) );

        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 15);
        set("count", 1);

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
}

int ask_fuwei()
{
 say("林震南炫耀地説：我們林家三代走鏢，一來仗着先祖遠圖公當年闖下的威名，二\n"
     "來靠著我們林家家傳的玩藝兒不算含糊，這才有今日的局面，成為大江以南首屈\n"
     "一指的大鏢局。江湖上提到『福威鏢局』四字，誰都要翹起大拇指，説一聲：『\n"
     "好福氣！好威風！』哈哈，哈哈！\n");
 set_temp("marks/林1", 1, this_player());
 return 1;
}

int ask_yuantu()
{
        if( query_temp("marks/林1", this_player()) )
        {
 say("林震南磕一磕煙斗，説道：遠圖公是我的祖父，福威鏢局是他一手創辦的。當年\n"
     "祖父以七十二路辟邪劍法開創鏢局，當真是打遍黑道無敵手。其時白道上英雄見\n"
     "他太過威風，也有去找他比試武藝的，青城派掌門餘觀主的師父長青子少年之時\n"
     "便在他辟邪劍法下輸了幾招。\n");
                set_temp("marks/林2", 1, this_player());
                return 1;
        }
        else
        {
                say("林震南説道：遠圖公是我的祖父。\n");
                return 1;
        }
}

int ask_bixie()
{
        int p1, p2, p3, p4;

        if( query("passwd", this_player()) )
        {
                say("林震南不悦地説道：我不是都告訴你了嗎？我的劍法不及先祖。\n");
        }
        else if( query_temp("marks/林2", this_player()) )
        {
 say("林震南一驚，説道：你怎麼知道的？噢，我剛才説露嘴了。嗨，在下的功夫外人\n"
     "不知底細，其實及不上先祖。。\n");
                write("林震南頓一頓，接着對你低聲説：先祖去世前，曾給家父留下");
                p1=random(4)+1;
                p2=random(4)+1;
                p3=random(4)+1;
                p4=random(4)+1;
                set("passwd", p1*1000+p2*100+p3*10+p4, this_player());
        write(CHINESE_D->chinese_number(p1)+"千"+CHINESE_D->chinese_number(p2)+
        "百"+CHINESE_D->chinese_number(p3)+"十"+CHINESE_D->chinese_number(p4));
        write("個\n銅錢，我一直未解其中奧祕。\n");
        }
        else
        {
                message("vision",
        HIY "林震南勃然大怒，喝道：你也窺視我們林家的辟邪劍譜？！我跟你拼了！\n"
        NOR, environment(), this_object() );
        kill_ob(this_player());
        }
        delete_temp("marks/林1", this_player());
        delete_temp("marks/林2", this_player());
        return 1;
}

int ask_tong()
{
        int p, p1, p2, p3, p4;

        if( !(p=query("passwd", this_player())) )
        {
                say("林震南一臉譏笑的樣子，説：怎麼混到這一步了到處要錢？\n");
        }
        else
        {
        write("林震南低聲説：先祖去世前，曾給家父留下");
        p1=(int)p/1000;
        p2=(int)(p-p1*1000)/100;
        p3=(int)(p-p1*1000-p2*100)/10;
        p4=(int)(p-p1*1000-p2*100-p3*10);
        write(CHINESE_D->chinese_number(p1)+"千"+CHINESE_D->chinese_number(p2)+
        "百"+CHINESE_D->chinese_number(p3)+"十"+CHINESE_D->chinese_number(p4));
        write("個\n銅錢，我一直未解其中奧祕。\n");
        }
        return 1;
}

int ask_baobiao()
{
        object me = this_player();
        object cart,biaotou,room,fsilver;
        int i;

        if( query("age", me)<18 )
        {
message_vision(HIY"$N又對$n説道：“小孩子家保什麼鏢！”\n"NOR,this_object(),me);
                return 1;
        }
        if( query("combat_exp", me)<10000 )
        {
message_vision(HIY"$N又對$n説道：“你那點能耐也想押鏢？再練兩年去！”\n"NOR,this_object(),me);
                return 1;
        }
        i = random(sizeof(destcity));

//        if (!wizardp(me)) return 0;
        if( query_temp("fuwei_dest", me) )
        {
message_vision(HIY"$N對$n説道：“你不是去了"+query_temp("fuwei_dest", me)+"了麼？還在這磨蹭！”\n"NOR,this_object(),me);
                return 1;
        }
        if (query("count") > 0)
        {
                cart = new(__DIR__"obj/cart");
                set("guarded",query("id",  me), cart);
                set("guardby",query("name",  me), cart);
                fsilver = new(__DIR__"obj/fake-silver");
                set("name", chinese_number(100000+random(10)*10000)+"兩"HIW"白銀"NOR, fsilver);
                fsilver->move(cart);
                biaotou = new(__DIR__"biaotou");
                set("leader_name",query("id",  me), biaotou);
                if (! room = find_object("/d/fuzhou/biaojudy") )
                        room = load_object("/d/fuzhou/biaojudy");
                cart -> move(room);
                biaotou -> move(room);
                addn("count",-1);
message_vision(HIY"$N對$n説道：“你來得正好，局裏眼下有批貨送往"+destcity[i]+"分局。你就去辛苦一趟吧！”\n"NOR, this_object(), me);
message_vision(HIY"$N又對$n説道：“你先去賬房交了押金再上路。”\n"NOR, this_object(), me);
                set_temp("fuwei_prepare", 1, me);
                delete_temp("fuwei_ready", me);
                set_temp("fuwei_destm", destmanager[i], me);
                set_temp("fuwei_dest", destcity[i], me);
                call_out("newjob",600,this_object());
                return 1;
        }
        else
        {
                message_vision(HIG"$N對$n説道：“你來得不巧，我們鏢局的貨剛上路。”\n"NOR, this_object(), me);
                return 1;
        }
}

void newjob()
{
        if (query("count") <= 0) addn("count",1);
        remove_call_out("newjob");
        call_out("newjob", 600);
}
