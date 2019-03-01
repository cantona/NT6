#include <ansi.h>

inherit ITEM;

mapping *long_desc = ({
 ([ "name":HIW"赤壁圖"NOR,
    "long": "\n
                    《赤壁圖》
此圖寫東坡赤壁泛舟景，筆意圓硬，如鋼針鐫鐵。畫山窮其凹凸，
寫水狀其盤渦，古畫中面目之特立者。原為項元汴所藏，題為“北
宋朱銳畫赤壁圖，趙閒閒追和坡仙詞真跡”，後人從之。考元遺山
集中，有題趙閒閒書赤壁詞，末雲：“赤壁圖，武元直所繪。”故
此圖實為武元直作。\n",]),

([ "name":YEL"虎溪三笑圖"NOR,
   "long": "\n
                   《虎溪三笑圖》 
虎溪三笑故事，廬山記雲：“遠法師居廬阜三十余年，影不出山，
跡不入俗，送客過虎溪，虎輒鳴號。昔陶元亮居栗裡，山南陸修靜
亦有道之士。遠師嘗送此二人，與語道合，不覺過之，因相與大笑。\n",]),

([ "name":GRN"溪山行旅圖"NOR,
   "long": "\n
                   《溪山行旅圖》
鬱鬱峨峨，其厚重渾淪，直似真山壓面；邱陵寺宇，林麓森森，棧
橋高架于危流，馱隊安行陌上。構景之妙，可雲獨至。全幅多用逆
筆，故老辣渾成，如鈍刀刮鐵，是傳世范(寬)畫極精之品。\n",]),

([ "name":HIY"文姬歸漢圖"NOR,
   "long": "\n
                   《文姬歸漢圖》
李唐所繪畫冊，本幅均絹本，均設色畫。是冊寫《胡茄十八拍》詩
意，此頁為第十三拍，幅上配原詩。\n",]),

([ "name":CYN"宮樂圖"NOR,
   "long": "\n
                     《宮樂圖》
本幅無作者名款，畫女樂十二人。十人圍案而坐，中四人正吹奏笙、
簫、古箏與琵琶諸樂器；侍立二人中，一人持拍相和；其余眾人坐
聽，狀至閒適。此圖石渠寶笈原標名元人畫，然審其人物體態豐腴，
開臉留三白，發髻衣飾，設色畫法皆系晚唐作風。\n",]),

([ "name":MAG"枇杷猿戲圖"NOR,
   "long": "\n
                   《枇杷猿戲圖》
枇杷一株，樹幹橫斜自右而上，一枝左垂下掛，覺老樹盤空，紙外
有畫，布局新意別出。一猿掛枝下墜，如人之嬉戲秋千；一猿距幹
注目，如人之旁觀袖手，真能得物之情。至于用墨之精，用筆之穩，
用色之雅，尤有過人處，是宋無款畫大幅中之精品。\n",]),

([ "name":YEL"明皇幸蜀圖"NOR,
   "long": "\n
                   《明皇幸蜀圖》
天寶十四年（七五五），安祿山舉兵反，陷長安，明皇幸蜀避之。
畫中著朱衣者即明皇。騎三驥照夜白，出棧道飛仙嶺下，乍見小橋，
馬驚不進。筆法精勁工細，青綠設色，絢燦華麗。\n",]),

([ "name":GRN"秋庭嬰戲圖"NOR,
   "long": "\n
                   《秋庭嬰戲圖》
本幅畫童嬰二人，撥棗為戲，精神專注，態貌如生，庭石芙蓉，秋光
滿紙；另一圓凳上列玩具，地上雙鈸，一俯一仰，無一物不工。有言
蘇畫嬰兒“著色鮮潤，體度如生，熟玩之，不啻相語言笑者，可為神
矣！”本軸雖無款，但確系蘇(漢臣)作。傳世多幅題為蘇漢臣嬰戲圖
中，以此畫為最佳。除各局部精描細繪，造型姿態掌握得宜外，更令
人嘆服的是傳神的技巧與意境的呈現。\n",]),

});

void create()
{        
         mapping i = long_desc[random(sizeof(long_desc))];

         set_name(i["name"], ({ "tu juan", "tu", "juan"}));
         set("long", i["long"]);

        if (clonep())
                set_default_object(__FILE__);
        else {               
//                set("value", 1);
                set("unit", "張");
                set("weight", 100);
                set("material", "paper");
                }
        setup();
}