// based on : https://github.com/nicolas-f/huzzah_esp32_pdm_mic/blob/master/pdm3.ino

#include "driver/i2s.h"
#include "dsps_fft2r.h"

#define READ_DELAY 100 // millisec
const i2s_port_t I2S_PORT = I2S_NUM_0;
const int BLOCK_SIZE = 512;
int samples[BLOCK_SIZE];
float plot_target;
#define SAMPLE_RATE 24000
long total_read = 0;

// http://www.schwietering.com/jayduino/filtuino/index.php?characteristic=be&passmode=hp&order=2&usesr=usesr&sr=24000&frequencyLow=100&noteLow=&noteHigh=&pw=pw&calctype=float&run=Send
//High pass bessel filter order=2 alpha1=0.0041666666666667 
class  FilterBeHp2
{
  public:
    FilterBeHp2()
    {
      v[0]=0.0;
      v[1]=0.0;
    }
  private:
    float v[3];
  public:
    float step(float x) //class II 
    {
      v[0] = v[1];
      v[1] = v[2];
      v[2] = (9.823849154958753660e-1 * x)
         + (-0.96497792085018785357 * v[0])
         + (1.96456174113331383246 * v[1]);
      return 
         (v[0] + v[2])
        - 2 * v[1];
    }
};

FilterBeHp2 filter;

void init_pdm() {
  
    esp_err_t err;

    i2s_config_t audio_in_i2s_config = {
         .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM),
         .sample_rate = SAMPLE_RATE,
         .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
         .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT, // although the SEL config should be left, it seems to transmit on right
         .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_LSB),
         .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1, // high interrupt priority
         .dma_buf_count = 4,
         .dma_buf_len = BLOCK_SIZE
        };
    
    // This function must be called before any I2S driver read/write operations.
    err = i2s_driver_install(I2S_PORT, &audio_in_i2s_config, 0, NULL);
    if (err != ESP_OK) {
      Serial.printf("Failed installing driver: %d\n", err);
      while (true);
    }
  
    // configure which pin on the ESP32 is connected to which pin on the mic:
    i2s_pin_config_t audio_in_pin_config = {
        .bck_io_num = I2S_PIN_NO_CHANGE, // not used
        .ws_io_num = AUD_BCLK,  // IO 15 clock pin
        .data_out_num = I2S_PIN_NO_CHANGE, // Not used
        .data_in_num = AUD_LRCLK  // data pin
    };
    
    err = i2s_set_pin(I2S_PORT, &audio_in_pin_config);
    if (err != ESP_OK) {
      Serial.printf("Failed setting pin: %d\n", err);
      while (true);
    }
}

void setup() {
    // Serial.begin(2000000);
    Serial.begin(115200);
    // Initialize the I2S peripheral
    init_pdm();
}

void process_samples() {
    size_t num_bytes_read;
    esp_err_t result = i2s_read(I2S_PORT, 
                                (char *)samples, 
                                BLOCK_SIZE,     // the doc says bytes, but its elements.
                                &num_bytes_read,
                                portMAX_DELAY); // no timeout
    if (result == ESP_OK && num_bytes_read > 0) {
        int samples_read = num_bytes_read / 4;
        total_read += samples_read;
        float sample;
        plot_target = 0;
        for(int i=0; i < samples_read; i++) {
          sample = filter.step((float)samples[i] / INT_MAX);
          plot_target += (sample * SHRT_MAX);
        }
        plot_target /= samples_read;
        Serial.print("Plot target: "); // to plot on the serial monitor
        Serial.println(plot_target);
    } else if (result != ESP_OK) {
        Serial.printf("Failed reading data: %d\n", result);
    }
}

void loop() {
    delay(READ_DELAY); 
    // Read multiple samples at once and calculate the sound pressure
    process_samples();
}