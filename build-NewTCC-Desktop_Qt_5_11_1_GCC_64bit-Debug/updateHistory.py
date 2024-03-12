import sys
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
from google_auth_oauthlib.flow import InstalledAppFlow
from googleapiclient.discovery import build
from googleapiclient.errors import HttpError

# If modifying these scopes, delete the file token.json.
SCOPES = ['https://www.googleapis.com/auth/spreadsheets']

SHEET_NAME = 'Update history'
SAMPLE_RANGE_NAME = "'Update history'!A1:A8"


def get_row(spreadsheet_id, range_name):
  # print(range_name)
  """
  Creates the batch_update the user has access to.
  Load pre-authorized user credentials from the environment.
  TODO(developer) - See https://developers.google.com/identity
  for guides on implementing OAuth2 for the application.
  """
  #creds, _ = google.auth.default()
  creds = Credentials.from_authorized_user_file("token.json", SCOPES)
  # pylint: disable=maybe-no-member
  try:
    service = build("sheets", "v4", credentials=creds)

    result = (
        service.spreadsheets()
        .values()
        .get(spreadsheetId=spreadsheet_id, range=range_name)
        .execute()
    )
    rows = result.get("values", [])
    #print(f"{rows}")

    res_list = []

    for item in rows:
        if item not in res_list: 
            res_list.append(item[0])
            # print(type(item))
            # print (item, end=" ")
    return res_list
  
  except HttpError as error:
    # print(f"An error occurred: {error}")
    # return error
    return None
  
def update_values(spreadsheet_id, range_name, value_input_option, _values):
    # print(f"{SAMPLE_RANGE_NAME}")
    creds = Credentials.from_authorized_user_file('token.json', SCOPES)

    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())

        # Save the credentials for the next run
        with open('token.json', 'w') as token:
            token.write(creds.to_json())

    try:
        service = build('sheets', 'v4', credentials=creds)
        values = _values  # Use the provided values parameter
        body = {
            'values': values
        }
        result = service.spreadsheets().values().append(
            spreadsheetId=spreadsheet_id, range=range_name,
            valueInputOption=value_input_option, body=body).execute()
        #return result
    except HttpError as error:
        print(f"An error occurred: {error}")
        return error

    # result = service.spreadsheets().values().get(
    #     spreadsheetId=spreadsheet_id,
    #     range=f'{SHEET_NAME}!A1:ZZ'
    # ).execute()
    
    r = get_row(SAMPLE_SPREADSHEET_ID, "'Update history'!A2:A")
    length = len(r)
    # print(f"{length}")

    update_requests = []

    sp = service.spreadsheets().get(
        spreadsheetId=spreadsheet_id
    ).execute()
    
    sheets = sp['sheets']
    for sheet in sheets:
        if sheet['properties']['title'] == SHEET_NAME:
            sheet_id = sheet['properties']['sheetId']
            break

    update_request = {
        "repeatCell": {
        "range": {
          "sheetId":sheet_id,
          "startRowIndex": length,
          "endRowIndex": length+1,
          "startColumnIndex": 5,
          "endColumnIndex": 6
        },
            "cell": {
             "userEnteredFormat": {
                "backgroundColor": {
                  "red": 0.7176470588,
                  "green": 0.8823529411,
                  "blue": 0.8039215686
                },
              }
            },
        "fields": "userEnteredFormat(backgroundColor)"
      }
    }
    update_requests.append(update_request)

    request_body = {
        'requests': update_requests
    }

    service.spreadsheets().batchUpdate(
        spreadsheetId=spreadsheet_id,
        body=request_body
    ).execute()

    # print('Borders added successfully.')
    print('Success')

if __name__ == '__main__':
    SAMPLE_SPREADSHEET_ID = open('spreadsheet_id', 'r').readline().strip()
    args = [string[1:] for string  in sys.argv]
    update_values(SAMPLE_SPREADSHEET_ID, SAMPLE_RANGE_NAME, 'USER_ENTERED',
                  [
                      args[1:]
                  ])