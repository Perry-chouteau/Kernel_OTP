# OTP Kernel Module

## Description

OTP stands for One Time Password.\
This project provides an OTP using a Loadable Kernel Module (LKM) to generate OTP codes in multiple ways.

## Developers

- Perry Chouteau (perry.chouteau@outlook.com)
- Erwan Cariou
- Vincent Mardirossian

For any issues or inquiries, please create an issue or email Perry Chouteau at perry.chouteau@outlook.com.

## Usage

### Insert Module

To insert the OTP kernel module, follow these steps:

1. Navigate to the project directory:
   ```sh
   cd project/
   ```

2. Build the module:
   ```sh
   make
   ```

3. Remove any existing instance of the module:
   ```sh
   sudo rmmod otp.ko
   ```

4. Insert the new module:
   ```sh
   sudo insmod otp.ko
   ```

### Get a Code

To retrieve an OTP code, use the following command:
```sh
sudo cat /dev/otp
```

### Edit Parameters

You can edit the module parameters using the following commands:

- Edit the timeout (integer):
  ```sh
  sudo sh -c "echo 5 > /sys/module/otp/parameters/timeout"
  ```

- Edit the client key (string):
  ```sh
  sudo sh -c "echo ourkey > /sys/module/otp/parameters/client_key"
  ```

- Edit the OTP type (0 = loopcode, 1 = gencode with client key):
  ```sh
  sudo sh -c "echo 0 > /sys/module/otp/parameters/otp_type"
  ```

### SysFS Integration

You may also use the filesystem to change the parameters !

1. **Verify the SysFS Entries:**

   After loading the module, check if the SysFS entries have been created by navigating to the otp directory:
   ```sh
   cd /sys/kernel/otp
   ls
   ```
   You should see the `client_key`, `timeout`, and `otp_type` files.

2. **Read the SysFS Entries:**

   Use the `cat` command to read the values of the SysFS entries:
   ```sh
   cat client_key
   cat timeout
   cat otp_type
   ```

3. **Write to the SysFS Entries:**

   Use the `echo` command to write new values to the SysFS entries:
   ```sh
   echo "new_client_key" | sudo tee client_key
   echo 20 | sudo tee timeout
   echo 1 | sudo tee otp_type
   ```
   After writing new values, read the entries again to verify the changes.