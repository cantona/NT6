// 天氣預報精靈
// 從網絡上抓取信息，預報天氣
// 本例子為抓取來自："202.106.184.193"的天氣預報信息。

#include <runtime_config.h>
#include <getconfig.h>
#include <net/socket.h>
#include <ansi.h>

// 202.106.184.193
// lxtx 202.103.25.171 4000
#define SITE "202.98.123.126 3000"
#define MAX_PENDING_INPUT 1000

inherit F_DBASE;

int check_time();
void close();
void send_to_remote();
void local_input(string str);

int fd;
string smsg;

void create()
{
      set("channel_id", "網際精靈");
      seteuid(getuid());
      //check_time();
}

void local_input(string str)
{
        if (str == "CLOSE")
        {
                write("用戶斷開了連接。\n");
                destruct(this_object());
                return;
        }

        input_to("local_input");

        if (strlen(str) + strlen(str) < MAX_PENDING_INPUT)
        {
                smsg += str + "\n";
                if (find_call_out("send_to_remote") == -1)
                        send_to_remote();
        } else
                write("你輸入的太多了...\n");
}

int check_time()
{
      mixed* times = localtime(time());
      int hours = times[2];
      int fd, ret;

      if(1)
      {
             fd = socket_create(STREAM, "read_callback", "close_callback");

             if(fd < 0)
             {
                   write("socket_create error " + socket_error(fd) + "\n");
                   socket_close(fd);
                   return 1;
             }
       }
       ret = socket_connect(fd, SITE,
                            "read_callback",
                            "write_callback");

       if (ret != EESUCCESS)
       {
             write("網絡連接錯誤！\n");
             socket_close(fd);
             return 1;
       }

       input_to("local_input");
       remove_call_out("close");
       call_out("close", 10);

       return 1;
}

void read_callback(int fd, mixed mess)
{
        if (! mess)return;

        CHANNEL_D->do_channel(this_object(), "wiz", mess);     
}

void write_callback(int fd)
{
        send_to_remote();
        return;
}

void close_callback(int fd)
{
       return;
}

void send_to_remote()
{
        switch (socket_write(fd, smsg))
        {
        case EESUCCESS:
                smsg = "";
                return;

        case EECALLBACK:                
                smsg = "";
                return;

        case EEWOULDBLOCK:
                // 發送數據阻塞
                call_out("send_to_remote", 1);
                return;

        default:
                // 發送失敗
                return;
        }
}

void close()
{        
        // 超時關閉連接
        socket_close(fd);
 
        write("OK CLOSED!\n");
        return;
}
