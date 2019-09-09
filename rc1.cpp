#define BUF_SIZE 1000

std::string init_rc() {

  long count_hostname, count_env;

  std::string write_to_rc_string;

  struct passwd *p;
  uid_t  uid;

  char wrie_buf[BUF_SIZE];

  char buf_env[BUF_SIZE];
  char buf_hostname[BUF_SIZE];
  
  char src_env[17]= "/etc/environment";
  char src_hostname[14] = "/etc/hostname";

  char _uname[7]="UNAME=";
  char _uid[5]="UID=";
  char _gid[5]="GID=";
  char _home[6]="HOME=";
  char _shell[7]="SHELL=";
  char _path[6]="PATH=";
  char _hostname[10]="HOSTNAME=";
  char _ps1[5]="PS1=";

  
  /* fetching globall env */

  int fd_env = open(src_env,O_RDONLY);
  if(fd_env == -1){
    perror("env fd error occurs");
  }else{
    count_env = read(fd_env,buf_env,BUF_SIZE);
    buf_env[count_env-1]='\0';
    close(fd_env);
  }
  /* fetching hostname */

  int fd_hostname = open(src_hostname,O_RDONLY);
  if(fd_hostname == -1){
    perror("hostname fd error occurs");
  }else{
    count_hostname = read(fd_hostname,buf_hostname,BUF_SIZE);
    close(fd_hostname);
    buf_hostname[count_hostname-1]='\0';
  }

  if ((p = getpwuid(uid = getuid())) == NULL)
  {
          perror("rctest.cpp::error locating uid");
          exit(-1);
  }
  write_to_rc_string+=convertToString(_ps1,sizeof(_ps1)-1);
  
  if(p->pw_uid == 0){
    write_to_rc_string+='#';
  }else{
  write_to_rc_string+='$';
  }

  write_to_rc_string+='\n';

  
  write_to_rc_string+=convertToString(_uname,strlen(_uname));
  write_to_rc_string+=convertToString(p->pw_name,strlen(p->pw_name));
  write_to_rc_string+='\n';

  write_to_rc_string+=convertToString(_uid,strlen(_uid));
  write_to_rc_string+= std::to_string(p->pw_uid);
  write_to_rc_string+='\n';
  
  write_to_rc_string+=convertToString(_gid,strlen(_gid));
  write_to_rc_string+=std:: to_string(p->pw_gid);
  write_to_rc_string+='\n';

  write_to_rc_string+=convertToString(_home,strlen(_home));
  write_to_rc_string+=convertToString(p->pw_dir,strlen(p->pw_dir));
  write_to_rc_string+='\n';

  write_to_rc_string+=convertToString(_shell,strlen(_shell));
  write_to_rc_string+=convertToString(p->pw_shell,strlen(p->pw_shell));
  write_to_rc_string+='\n';

  write_to_rc_string+=convertToString(_hostname,strlen(_hostname));
  write_to_rc_string+=convertToString(buf_hostname,strlen(buf_hostname));
  write_to_rc_string+='\n';

  //write_to_rc_string+=convertToString(_home,sizeof(_home)-1);
  write_to_rc_string+=convertToString(buf_env,strlen(buf_env));
  write_to_rc_string+='\n';
  write_to_rc_string+="HISTSIZE=1000";  
  write_to_rc_string+='\n';
   
  return write_to_rc_string;

    //cout<<write_to_rc_string;

    //int rcfd = open("myrc",O_WRONLY|O_CREAT,0664);

    //write(rcfd,wrie_buf,); 
 
  //printf("%s\n",buf_env);
 
  //printf("%s\n",buf_hostname);
}

std::string getPrompt(){

  std::string s;
  struct passwd *p;
  uid_t  uid;
  long count_hostname;
  char buf_hostname[BUF_SIZE];

  char src_hostname[14] = "/etc/hostname";

  if ((p = getpwuid(uid = getuid())) == NULL)
  {
          perror("rctest.cpp::error locating uid");
          exit(-1);
  }

  int fd_hostname = open(src_hostname,O_RDONLY);
  if(fd_hostname == -1){
    perror("hostname fd error occurs");
  }else{
    count_hostname = read(fd_hostname,buf_hostname,BUF_SIZE);
    close(fd_hostname);
    buf_hostname[count_hostname-1]='\0';
  }

  s+=convertToString(p->pw_name,strlen(p->pw_name));

  s+='@';

  s+=convertToString(buf_hostname,strlen(buf_hostname));

  // char* directory = getcwd(buf_hostname,BUF_SIZE);

  // s+=convertToString(directory,strlen(directory));


if(p->pw_uid == 0){
    s+='#';
  }else{
  s+='$';
  }
  return s;
}



// int main(){

//   cout<<getPrompt();

//   return 0;
// }