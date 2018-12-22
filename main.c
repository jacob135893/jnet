#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int create_network(int argc, char *argv[]);
void reverse_bytes(int *num);

int main(int argc, char *argv[]) {
    int result;
    if(argc < 2) {
        return 0;
    }
    if(strcmp(argv[1],"create")==0) {
        printf("Starting network creation\n");
        result = create_network(argc,argv);
        if(result==-1) {
            printf("Network creation failed\n");
        } else {
            printf("Network creation successful\n");
        }
    } else if(strcmp(argv[1],"train")==0) {
        printf("Starting network training\n");
    }
}

void reverse_bytes(int *num) {
    int n;
    n = (*num>>24)&0xff |
            ((*num<<8)&0xff0000) |
            ((*num>>8)&0xff00) |
            ((*num<<24)&0xff000000);
    *num = n;
}

int create_network(int argc, char *argv[]) {
    FILE *input_file;
    FILE *output_file;
    char *input_file_name;
    char *output_file_name;
    long int byte_count;
    int input_count;
    int output_count;
    int layer_count;
    int *layer_sizes;
    int layer_index;
    int size;
    if(argc < 4) {
        return -1;
    }
    input_file_name = argv[2];
    output_file_name = argv[3];
    input_file = fopen(input_file_name,"r");
    output_file = fopen(output_file_name,"w");
    fseek(input_file, 0 , SEEK_END);
    byte_count = ftell(input_file);
    if(byte_count==-1) {
        return -1;
    }
    rewind(input_file);
    fread(&input_count,4,1,input_file);
    fwrite(&input_count,4,1,output_file);
    reverse_bytes(&input_count);
    printf("Input neuron count: %d\n", input_count);
    fread(&output_count,4,1,input_file);
    fwrite(&output_count,4,1,output_file);
    reverse_bytes(&output_count);
    printf("Output neuron count: %d\n", output_count);
    fread(&layer_count,4,1,input_file);
    fwrite(&layer_count,4,1,output_file);
    reverse_bytes(&layer_count);
    printf("Hidden layer count: %d\n", layer_count);
    layer_sizes = malloc((layer_count + 2) * sizeof(int));
    printf("Initializing\n");
    *layer_sizes = input_count;
    *(layer_sizes+layer_count) = output_count;
    for(layer_index = 1; layer_index <= layer_count; layer_index++) {
        fread(&size,4,1,input_file);
        fwrite(&size,4,1,output_file);
        reverse_bytes(&size);
        *(layer_sizes+layer_index) = size;
        printf("Hidden layer %d count: %d\n",layer_index,size);
    }
    fclose(input_file);
    fclose(output_file);
    return 1;
}