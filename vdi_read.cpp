#include "vdi_read.h"

using namespace std;

int vdiOpen(VDIFile *vdi, char *fn){
  vdi->file = open(fn, O_RDWR);
  vdi->cursor = 0;
  if(vdi->file < 0) return 1;
  return vdi->file;
}

void vdiClose(VDIFile *f){
  close(f->file);
}

off_t vdiSeek(VDIFile *f, off_t offset, int whence){
  off_t location;
  if (whence == SEEK_SET){
    location= lseek(f->file, offset, whence);
    if(location < 0){
      cout << "Error seeking the vdi header" << endl;
      return 1;
    }
    f->cursor = location;
  }
  if (whence == SEEK_CUR){
    location = lseek(f->file, offset, whence);
    if (location < 0){
      cout << "Error seeking the vdi header" << endl;
      return 1;
    }
    f->cursor += offset;
  }
  if(whence == SEEK_END){
    location = lseek(f->file, offset, whence);
    if (location < 0){
      cout << "Error seeking the vdi header" << endl;
      return 1;
    }
    f->cursor = offset + f->fileSize;
  }
  return f->cursor;
}

ssize_t vdiRead(VDIFile *f, void *buf, ssize_t n){
  //cout << "value of buf before reading: " << buf << endl;
  ssize_t numBytes = read(f->file, buf, n);
  //cout << "Cursor " << f->cursor << endl;
  if(numBytes != n) {
    cout << "Error header not read correctly" << endl;
    return 1;
  }
  return 0;
}

/*ssize_t vdiWrite(VDIFile *f, void *buf, ssize_t n){
  f->fileStructure.write(buf, n);
  if(f->fileStructure){
    return n;
  }
  else{
    return -1;
  }
  
  return 0;
  }*/







  
